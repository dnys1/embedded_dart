#include <iostream>

#include <include/dart_api.h>
#include <include/dart_embedder_api.h>
#include <bin/elf_loader.h>

int main() {
    std::cout << "Initializing Dart" << std::endl;

    char *error = Dart_SetVMFlags(0, nullptr);
    if (error != nullptr) {
        std::cerr << "Error setting VM flags: " << error << std::endl;
        return 1;
    }

    char *init_error = nullptr;
    if (!dart::embedder::InitOnce(&init_error)) {
        std::cerr << "Error initializing: " << init_error << std::endl;
        return 1;
    }

    static const char *aot_path = "/Users/nydillon/dev/embedded_dart/bin/embedded_dart.aot";
    const uint8_t *vm_snapshot_data = nullptr;
    const uint8_t *vm_snapshot_instructions = nullptr;
    const uint8_t *core_isolate_snapshot_data = nullptr;
    const uint8_t *core_isolate_snapshot_instructions = nullptr;
    const char *elf_load_err = nullptr;
    const Dart_LoadedElf *loaded_elf = Dart_LoadELF(aot_path,
                                                    0,
                                                    &elf_load_err,
                                                    &vm_snapshot_data,
                                                    &vm_snapshot_instructions,
                                                    &core_isolate_snapshot_data,
                                                    &core_isolate_snapshot_instructions);
    if (elf_load_err != nullptr) {
        std::cerr << "Error loading ELF: " << elf_load_err << std::endl;
        return 1;
    }
    assert(loaded_elf != nullptr);

    Dart_InitializeParams params = {
            .version = DART_INITIALIZE_PARAMS_CURRENT_VERSION,
            .vm_snapshot_data = vm_snapshot_data,
            .vm_snapshot_instructions = vm_snapshot_instructions,
            .start_kernel_isolate = false,
    };
    char* initialize_error = Dart_Initialize(&params);
    std::cout << "Dart initialized with error: "
              << (initialize_error != nullptr ? initialize_error : "null")
              << std::endl;

    return 0;
}
