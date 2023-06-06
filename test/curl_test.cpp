#include <curl/curl.h>
#include <iostream>
#include <string>

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
	std::string *response = static_cast<std::string *>(userdata);
	response->append(ptr, size * nmemb);
	return size * nmemb;
}

std::pair<bool, std::string> send_req(bool is_post, const std::string &url,
                                      const std::string &body) {
	CURL *curl = curl_easy_init();  // 初始化curl
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());  // 设置请求URL
		if (is_post) {
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
		}
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);  // 支持重定向
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
		                 write_callback);  // 设置回调函数
		std::string response;
		curl_easy_setopt(curl, CURLOPT_WRITEDATA,
		                 &response);  // 设置回调函数参数
		CURLcode result_code = curl_easy_perform(curl);  // 执行请求
		if (result_code != CURLE_OK) {
			return std::make_pair(false, curl_easy_strerror(result_code));
		} else {
			return std::make_pair(true, response);
		}
		curl_easy_cleanup(curl);  // 释放curl资源
	}
	return std::make_pair(false, "");
}

std::pair<bool, std::string> get(const std::string &url) {
	return send_req(false, url, "");
}

std::pair<bool, std::string> post(const std::string &url,
                                  const std::string &body) {
	return send_req(true, url, body);
}

int main(void) {
	auto res = get("http://baidu.com");
	std::cout << res.first;
	std::cout << res.second;

	res = post("http://baidu.com", "hello");
	std::cout << res.first;
	std::cout << res.second;

	return 0;
}
