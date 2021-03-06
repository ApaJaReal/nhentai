#include "curl.hpp"
#include "out.hpp"
#include "utils.hpp"

#include <cstring>
#include <string>
#include <curl/curl.h>

static inline size_t write_callback(char* buf, size_t size, size_t nmemb, std::string* src) {
    *src += std::string(buf);
    return size*nmemb;
}

namespace curl {
    std::string download_html(const std::string& url) {
        std::string src;
        CURL* curl_get_html = curl_easy_init();
        curl_easy_setopt(curl_get_html, CURLOPT_URL, url.c_str());
        /* send the data to the call back function */
        curl_easy_setopt(curl_get_html, CURLOPT_WRITEFUNCTION, &write_callback);
        /* give the callback function mem struct */
        curl_easy_setopt(curl_get_html, CURLOPT_WRITEDATA, &src);
        /* fail if we get a 404 or any other error, size will be 0 to identify */
        curl_easy_setopt(curl_get_html, CURLOPT_FAILONERROR, 1);
        curl_easy_perform(curl_get_html);
        curl_easy_cleanup(curl_get_html);
        return src;
    }

    bool download_file(const std::string& url, const std::string& output) {
        /* our curl objects */
        CURL* get_file;
        CURLcode get_file_result;
        FILE* file_output;

        /* only download if the file doesn't exist */
        if (!utils::exist_test(output.c_str())) {
            get_file = curl_easy_init();
            file_output = ::fopen(output.c_str(), "w");
            if (file_output == NULL) {
                return false;
            }
            /* set url */
            curl_easy_setopt(get_file, CURLOPT_URL, url.c_str());
            curl_easy_setopt(get_file, CURLOPT_WRITEFUNCTION, NULL);
            /* fail if we get an error */
            curl_easy_setopt(get_file, CURLOPT_FAILONERROR, 1);
            /* write data to the image file */
            curl_easy_setopt(get_file, CURLOPT_WRITEDATA, file_output);
            get_file_result = curl_easy_perform(get_file);

            /* file download fail */
            if (get_file_result) {
                ::fclose(file_output);
                ::remove(output.c_str());
                curl_easy_cleanup(get_file);
                return false;
            }
            curl_easy_cleanup(get_file);
            ::fclose(file_output);
        }
        return true; 
    }
}