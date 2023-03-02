#include <curl/curl.h>
#include <iostream>
#include <map>

// 回调函数，用于处理接收到的数据
size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata) {
	std::string* response = static_cast<std::string*>(userdata);
	response->append(ptr, size * nmemb);
	return size * nmemb;
}

void do_get(const std::string& url_base, const std::string& algo_name,
            std::map<std::string, std::string> params) {
	CURL* curl = curl_easy_init();  // 初始化curl
	if (curl) {
		std::string url = url_base;
		url = url.append("/").append(algo_name).append("?");
		for (auto it : params) {
			url =
			    url.append(it.first).append("=").append(it.second).append("&");
		}
		std::cout << url << std::endl;

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());    // 设置请求URL
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);  // 支持重定向
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
		                 write_callback);  // 设置回调函数
		std::string response;
		curl_easy_setopt(curl, CURLOPT_WRITEDATA,
		                 &response);                // 设置回调函数参数
		CURLcode result = curl_easy_perform(curl);  // 执行请求
		if (result != CURLE_OK) {
			// TODO
			std::cerr << "curl_easy_perform() failed: "
			          << curl_easy_strerror(result) << std::endl;
		} else {
			std::cout << "Response: " << response << std::endl;
		}
		curl_easy_cleanup(curl);  // 释放curl资源
	}
}

int main() {
	std::string base_url = "http://192.168.8.212:8080/algo";
	std::map<std::string, std::string> params{{"root", "41635277"},
	                                          {"max_iter", "100"}};

	do_get(base_url, "degree_nstep_from_root", params);
	return 0;
}
