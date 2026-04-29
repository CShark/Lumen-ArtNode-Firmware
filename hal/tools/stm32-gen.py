import re
import json
import os
import sys
import glob
from collections import defaultdict
from pathlib import Path

if len(sys.argv) != 2:
    print("Usage: stm32-gen.py <name of chip>")
    sys.exit(1)


def gpio(json, chip):
    ports = defaultdict(list)
    pins = json["cores"][0]["pins"]

    for pin in pins:
        name = pin["name"]
        match = re.match(r"P([A-Z])(\d+)", name)
        if not match:
            continue

        port = match.group(1)
        idx = int(match.group(2))

        ports[port].append(idx)

    result = []

    result.append("#pragma once")
    result.append("#include \"" + chip.lower() + "xx.h\"")
    result.append("#include <cstdint>")
    result.append("")
    result.append("namespace hal::gpio {")
    result.append("    namespace internal {")

    for port, indices in sorted(ports.items()):
        indices = sorted(set(indices))

        result.append(f"        struct Port{port} {{")
        result.append(f"            static inline GPIO_TypeDef *reg() {{ return GPIO{port}; }}")
        result.append(f"            static constexpr bool isPinValid(uint8_t idx) {{")
        result.append(f"                switch (idx) {{")

        for i in indices:
            result.append(f"                case {i}:")

        result.append(f"                    return true;")
        result.append(f"                default:")
        result.append(f"                    return false;")
        result.append(f"                }}")
        result.append(f"            }}")
        result.append(f"        }};\n")

    result.append("     }")
    result.append("")

    result.append("""    template <typename T>
    concept PortTrait = requires(uint8_t idx) {
        { T::isPinValid(idx) } -> std::convertible_to<bool>;
        { T::reg() } -> std::convertible_to<GPIO_TypeDef *>;
    };""")

    result.append("")
    result.append("""    template <PortTrait Port, uint8_t Idx>
    struct Pin;""")

    result.append("")
    for port, indices in sorted(ports.items()):
        indices = sorted(set(indices))

        for i in indices:
            result.append(f"    using P{port}{i} = Pin<internal::Port{port}, {i}>;")

    result.append("}")
    result = "\n".join(result)

    return result

def uart(json, chip):
    uarts = [x for x in json["cores"][0]["peripherals"] if re.match(r"US?ART\d+", x['name'])]
    
    result = []
    result.append("#pragma once")
    result.append("#include \"" + chip.lower() + "xx.h\"")
    result.append("#include \"hal/gpio.h\"")
    result.append("#include <cstdint>")
    result.append("")
    result.append("#define MAP_UART_AF(uart, pin, role, af) \\")
    result.append("    template<>\\")
    result.append("    struct internal::UartAfMapping<uart, pin, role> {\\")
    result.append("        static constexpr int afValue = af;\\")
    result.append("    }")
    result.append("")
    result.append("namespace hal::uart {")
    result.append("    namespace internal {")

    result.append("        struct TagRx {};")
    result.append("        struct TagTx {};")
    result.append("        struct TagCts {};")
    result.append("        struct TagRts {};")
    result.append("        struct TagNss {};")
    result.append("        struct TagDe {};")
    result.append("        struct TagCk {};")
    result.append("")
    result.append("        template<typename Uart, typename Pin, typename Role>")
    result.append("        struct UartAfMapping {")
    result.append("            static constexpr int afValue = -1;")
    result.append("        };")

    result.append("    }")
    result.append("")

    for item in sorted(uarts, key=lambda item: item['name']):
        result.append(f"    struct {item["name"].title()} {{")
        result.append(f"        static constexpr uintptr_t reg = {item["name"].upper()}_BASE;")
        result.append(f"        static constexpr uint8_t irq = {item["name"].upper()}_IRQn;")
        result.append(f"        static constexpr char name[] = \"{item["name"].upper()}\";")
        result.append("")
        result.append(f"        static void rcc_enable() {{")
        result.append(f"            RCC->{item["rcc"]["enable"]["register"]} |= RCC_{item["rcc"]["enable"]["register"]}_{item["rcc"]["enable"]["field"]};")
        result.append(f"            (void)RCC->{item["rcc"]["enable"]["register"]};")
        result.append(f"        }}")
        result.append("")
        result.append(f"        static void rcc_disable() {{")
        result.append(f"            RCC->{item["rcc"]["enable"]["register"]} &= ~RCC_{item["rcc"]["enable"]["register"]}_{item["rcc"]["enable"]["field"]};")
        result.append(f"        }}")
        result.append("")
        result.append(f"        static void rcc_reset() {{")
        result.append(f"            RCC->{item["rcc"]["reset"]["register"]} |= RCC_{item["rcc"]["reset"]["register"]}_{item["rcc"]["reset"]["field"]};")
        result.append(f"            RCC->{item["rcc"]["reset"]["register"]} &= ~RCC_{item["rcc"]["reset"]["register"]}_{item["rcc"]["reset"]["field"]};")
        result.append(f"        }}")
        result.append(f"    }};")
        
        for af in item["pins"]:
            match = re.match(r"P([A-Z])(\d+)", af["pin"])
            result.append(f"    MAP_UART_AF({item["name"].title()}, gpio::P{match.group(1)}{match.group(2)}, internal::Tag{af["signal"].title()}, {af["af"]});")
        
        result.append("")

    result.append("}")
    result.append("")
    result.append("#undef MAP_UART_AF")
    result = "\n".join(result)
    
    return result

# List all available json files
stm32files = glob.glob(
    "tools/stm32-data-generated/data/chips/" + sys.argv[1].upper() + "*.json")
stm32files = sorted(tuple((file, os.path.getsize(file))
                    for file in stm32files), key=lambda item: item[1], reverse=True)
with open(stm32files[0][0], "r", encoding="utf-8") as f:
    stm32json = json.load(f)

genDir = "gen/" + sys.argv[1].lower() + "/inc/hal/gen/"
Path(genDir).mkdir(parents=True, exist_ok=True)

with open(genDir + "gpio.h", "w+", encoding="utf-8") as f:
    f.write("// Auto generated file. Do not edit.\n")
    f.write(gpio(stm32json, sys.argv[1]))

with open(genDir + "uart.h", "w+", encoding="utf-8") as f:
    f.write("// Auto generated file. Do not edit.\n")
    f.write(uart(stm32json, sys.argv[1]))