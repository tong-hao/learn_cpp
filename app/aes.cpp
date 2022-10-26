#include <openssl/err.h>
#include <openssl/pem.h>
#include <iostream>

const unsigned int kBlockSize = 16;

bool aes256Encrypt(const unsigned char* key, const unsigned char* iv,
                   const std::string& ptext, std::string& ctext) {
	EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
	int rc = EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv);
	if (rc != 1) {
		// return Status::Error("EVP_EncryptInit_ex failed");
		return false;
	}

	// Recovered text expands upto kBlockSize
	ctext.resize(ptext.size() + kBlockSize);
	int out_len1 = static_cast<int>(ctext.size());

	rc = EVP_EncryptUpdate(ctx, reinterpret_cast<unsigned char*>(&ctext[0]),
	                       &out_len1,
	                       reinterpret_cast<const unsigned char*>(&ptext[0]),
	                       static_cast<int>(ptext.size()));
	if (rc != 1) {
		// return Status::Error("EVP_EncryptUpdate failed");
		return false;
	}

	int out_len2 = static_cast<int>(ctext.size()) - out_len1;
	rc = EVP_EncryptFinal_ex(
	    ctx, reinterpret_cast<unsigned char*>(&ctext[0]) + out_len1, &out_len2);
	if (rc != 1) {
		// return Status::Error("EVP_EncryptFinal_ex failed");
		return false;
	}

	EVP_CIPHER_CTX_free(ctx);
	// Set cipher text size now that we know it
	ctext.resize(out_len1 + out_len2);
	// return Status::OK();
	return true;
}

bool aes256Decrypt(const unsigned char* key, const unsigned char* iv,
                   const std::string& ctext, std::string& rtext) {
	EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
	int rc = EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv);
	if (rc != 1) {
		// return Status::Error("EVP_DecryptInit_ex failed");
		return false;
	}

	// Recovered text contracts upto kBlockSize
	rtext.resize(ctext.size());
	int out_len1 = static_cast<int>(rtext.size());

	rc = EVP_DecryptUpdate(ctx, reinterpret_cast<unsigned char*>(&rtext[0]),
	                       &out_len1,
	                       reinterpret_cast<const unsigned char*>(&ctext[0]),
	                       static_cast<int>(ctext.size()));
	if (rc != 1) {
		// return Status::Error("EVP_DecryptUpdate failed");
		return false;
	}

	int out_len2 = static_cast<int>(rtext.size()) - out_len1;
	rc = EVP_DecryptFinal_ex(
	    ctx, reinterpret_cast<unsigned char*>(&rtext[0]) + out_len1, &out_len2);
	if (rc != 1) {
		// logErrors();
		// return Status::Error("EVP_DecryptFinal_ex failed");
		return false;
	}

	EVP_CIPHER_CTX_free(ctx);
	// Set recovered text size now that we know it
	rtext.resize(out_len1 + out_len2);
	return true;
}

int main(int argc, char const* argv[]) {
	std::string kAesKeyBase64 = "241IYjd0+MKVhiXc0PWFetV7RhmsjTCJpZslOCPC5n8=";
	std::string kAesIvBase64 = "rjJJOkaaueQmwFTVtzBAxw==";

	std::string code = "abc";
	std::string aes256MachineCode;
	// const std::string aesKey = License::getAesKey();
	// const std::string aesIv = License::getAesIV();
	aes256Encrypt(reinterpret_cast<const unsigned char*>(kAesKeyBase64.c_str()),
	              reinterpret_cast<const unsigned char*>(kAesIvBase64.c_str()),
	              code, aes256MachineCode);

	std::cout << aes256MachineCode << std::endl;

	std::string decode;
	aes256Decrypt(reinterpret_cast<const unsigned char*>(kAesKeyBase64.c_str()),
	              reinterpret_cast<const unsigned char*>(kAesIvBase64.c_str()),
	              aes256MachineCode, decode);
	std::cout << decode << std::endl;

	return 0;
}

// link:  -lcrypto
