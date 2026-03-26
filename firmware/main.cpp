#include <stdio.h>
#include "esp_heap_caps.h"

void printMemoryStatus(const char* stage) {
    printf("\n=== %s ===\n", stage);

    printf("Heap total: %d bytes\n", heap_caps_get_total_size(MALLOC_CAP_8BIT));
    printf("Heap free: %d bytes\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));

    printf("Internal free: %d bytes\n", heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
    printf("DMA free: %d bytes\n", heap_caps_get_free_size(MALLOC_CAP_DMA));
    printf("PSRAM free: %d bytes\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
}

extern "C" void app_main() {

    // Step 1: Before allocation
    printMemoryStatus("Before Allocation");

    // Step 2: Allocate memory
    uint8_t* internal_buf = (uint8_t*) heap_caps_malloc(16 * 1024, MALLOC_CAP_INTERNAL);
    uint8_t* dma_buf      = (uint8_t*) heap_caps_malloc(8 * 1024, MALLOC_CAP_DMA);
    uint8_t* psram_buf    = (uint8_t*) heap_caps_malloc(64 * 1024, MALLOC_CAP_SPIRAM);

    // Step 3: After allocation
    printMemoryStatus("After Allocation");

    // 防止優化
    if (internal_buf && dma_buf && psram_buf) {
        printf("Memory allocated successfully\n");
    } else {
        printf("Memory allocation failed\n");
    }
}