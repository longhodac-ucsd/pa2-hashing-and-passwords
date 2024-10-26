#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <openssl/sha.h>
#include<assert.h>

// Milestone 1'

uint8_t hex_to_byte(unsigned char h1, unsigned char h2) {
    uint8_t byte = 0;

    // Convert first hex digit (h1)
    if (h1 >= '0' && h1 <= '9') {
        byte = (h1 - '0') << 4;  
    } else if (h1 >= 'A' && h1 <= 'F') {
        byte = (h1 - 'A' + 10) << 4;  
    } else if (h1 >= 'a' && h1 <= 'f') {
        byte = (h1 - 'a' + 10) << 4;  
    }

    // Convert second hex digit (h2)
    if (h2 >= '0' && h2 <= '9') {
        byte |= (h2 - '0');  
    } else if (h2 >= 'A' && h2 <= 'F') {
        byte |= (h2 - 'A' + 10);  
    } else if (h2 >= 'a' && h2 <= 'f') {
        byte |= (h2 - 'a' + 10);  
    }

    return byte;
}

void hexstr_to_hash(char hexstr[], unsigned char hash[32]) {
    for (int i = 0; i < 32; i++) {
        hash[i] = hex_to_byte(hexstr[2 * i], hexstr[2 * i + 1]);
    }
}

// Milestone 2

int8_t check_password(char password[], unsigned char given_hash[32]){
    unsigned char computed_hash[32]; 

    // Calculate the SHA256 Hash
    SHA256((unsigned char*)password, strlen(password), computed_hash);

    for (int i = 0; i < 32; i++){
        if (computed_hash[i] != given_hash[i]){
            return 0;
        }
    }
    return 1;

}

void test_hex_to_byte() {
    assert(hex_to_byte('c', '8') == 200);  // Corrected missing semicolon
    // You can add more test cases as needed
}

void test_hexstr_to_hash() {
    char hexstr[64] = "a2c3b02cb22af83d6d1ead1d4e18d916599be7c2ef2f017169327df1f7c844fd";
    unsigned char hash[32];
    hexstr_to_hash(hexstr, hash);

    // Print the hash for visual validation
    printf("Hash: ");
    for (int i = 0; i < 32; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    // Test assertions
    assert(hash[0] == 0xa2);
    assert(hash[31] == 0xfd);
}

const int testing = 1;

int main(int argc, char** argv) {
    if (testing) {
        test_hex_to_byte();
        test_hexstr_to_hash();
    }

    if (argc > 1 && strlen(argv[1]) == 64) {
        unsigned char hash[32];
        hexstr_to_hash(argv[1], hash);

        // Print the computed hash
        printf("Computed hash for input: ");
        for (int i = 0; i < 32; i++) {
            printf("%02x", hash[i]);
        }
        printf("\n");
    } else {
        printf("Usage: %s <64-char hex string>\n", argv[0]);
    }

    char hash_as_hexstr[] = "5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8"; // SHA256 hash for "password"
    unsigned char given_hash[32];
    hexstr_to_hash(hash_as_hexstr, given_hash);
    assert(check_password("password", given_hash) == 1);
    assert(check_password("wrongpass", given_hash) == 0);

    return 0;
}
