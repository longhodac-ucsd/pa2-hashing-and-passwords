// Long HoDac
// PA 2 - Password cracking
// 10/25/2024

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <openssl/sha.h>
#include<assert.h>

// Function prototypes
void test_hex_to_byte();
void test_hexstr_to_hash();
int8_t check_password(char password[], unsigned char given_hash[]);
int8_t crack_password(char password[], unsigned char given_hash[]);
void hexstr_to_hash(char hexstr[], unsigned char hash[32]);

const int testing = 1;

int main(int argc, char** argv) {
    // Run test cases if testing is enabled
    if (testing) {
        test_hex_to_byte();
        test_hexstr_to_hash();

        // Test check_password function
        char hash_as_hexstr1[] = "5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8"; // SHA256 hash for "password"
        unsigned char given_hash1[32];
        hexstr_to_hash(hash_as_hexstr1, given_hash1);

        assert(check_password("password", given_hash1) == 1);
        assert(check_password("wrongpass", given_hash1) == 0);

        // Test crack_password function
        char password_to_crack[] = "paSsword";
        unsigned char given_hash2[32];
        hexstr_to_hash(hash_as_hexstr1, given_hash2);

        int8_t match = crack_password(password_to_crack, given_hash2);
        assert(match == 1);
        assert(password_to_crack[2] == 's'); // Expect uppercase 'S' to be lowercased
        printf("All assertions passed.\n");
    }

    // Verify user input for hash conversion
    if (argc > 1 && strlen(argv[1]) == 64) {
        unsigned char user_hash[32];
        hexstr_to_hash(argv[1], user_hash);

        printf("Computed hash for input: ");
        int i;
        for (i = 0; i < 32; i++) {
            printf("%02x", user_hash[i]);
        }
        printf("\n");
    } else {
        printf("Usage: %s <64-char hex string>\n", argv[0]);
    }

    return 0;
}

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
    int i;
    for (i = 0; i < 32; i++) {
        hash[i] = hex_to_byte(hexstr[2 * i], hexstr[2 * i + 1]);
    }
}

// Milestone 2

int8_t check_password(char password[], unsigned char given_hash[32]){
    unsigned char computed_hash[32]; 

    // Calculate the SHA256 Hash
    SHA256((unsigned char*)password, strlen(password), computed_hash);

    int i;
    for (i = 0; i < 32; i++){
        if (computed_hash[i] != given_hash[i]){
            return 0;
        }
    }
    return 1;

}

// Milestone 3

int8_t crack_password(char password[], unsigned char given_hash[]){
    int pw_len = strlen(password);

    if(check_password(password, given_hash)){
        return 1;
    }

    int i;
    for(i = 0; i < pw_len; i++){
        char old_char = password[i];

        if (password[i] >= 'a' && password[i] <= 'z'){
            password[i] -= 32;
            if(check_password(password, given_hash)){
                return 1;
            }
            password[i] = old_char;
        }
        else if (password[i] >= 'A' && password[i] <= 'Z'){
            password[i] += 32;
            if(check_password(password, given_hash)){
                return 1;
            }
            password[i] = old_char;
        }

    }

    return 0;

}

// Testing functions

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


