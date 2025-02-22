#include "pkcs7_padding.h"

// Function to add PKCS#7 padding to the nanopb data.
size_t add_pkcs7_padding(const uint8_t *input, size_t input_len, uint8_t *output, size_t block_size) {
    // Copy the original data
    memcpy(output, input, input_len);

    // Calculate the number of padding bytes required.
    size_t pad_len = block_size - (input_len % block_size);
    if(pad_len == 0) {
        pad_len = block_size; // Always pad even if input_len is a multiple of block_size
    }

    // Append the padding bytes.
    for (size_t i = 0; i < pad_len; i++) {
        output[input_len + i] = (uint8_t)pad_len;
    }

    return input_len + pad_len;
}

// Function to remove PKCS#7 padding after decryption.
size_t remove_pkcs7_padding(uint8_t *data, size_t data_len) {
    if (data_len == 0) return 0;
    uint8_t pad_len = data[data_len - 1];
    // In a robust implementation, you should validate that all padding bytes are equal to pad_len.
    return data_len - pad_len;
}
