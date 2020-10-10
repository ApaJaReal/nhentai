#include <stdio.h>
#include <curl/curl.h>

#include "download.h"

int writeDataI = 0;

static size_t writeCallBack(char* buf, size_t size, size_t nmemb, void* up) {
    // buf is a pointer to the data that curl has for us
    // size*nmemb is the size of the buffer
    for (int c = 0; c < size*nmemb; c++) {  
        storedData[writeDataI] = buf[c];
        writeDataI++;
    }
    // tell curl how many bytes we handled
    return size*nmemb;
}

int getHtml(const char* downloadUrl) {
    CURL* getId; // our curl object
    CURLcode getIdResult;
    getId = curl_easy_init(); // easy int
    curl_easy_setopt(getId, CURLOPT_URL, downloadUrl); // make url the curl_url
    curl_easy_setopt(getId, CURLOPT_WRITEFUNCTION, &writeCallBack);
    getIdResult = curl_easy_perform(getId); // perform operation
   
    if (getIdResult) {
        writeDataI = 0;
        curl_easy_cleanup(getId);
        return 0;
    }
    writeDataI = 0;
    return 1;
}

int doDownload(char* url, char* file) {
    CURL* image;
    CURLcode imgresult;
    FILE *fp;

    // printf("%s\n", url);
    // if (!existTest() {
        image = curl_easy_init();
        fp = fopen(file, "w");
        if (fp == NULL) {
            printf("Unable To Create Image\n");
        }
        curl_easy_setopt(image, CURLOPT_URL, url);
        curl_easy_setopt(image, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(image, CURLOPT_FAILONERROR, 1);
        curl_easy_setopt(image, CURLOPT_WRITEDATA, fp);
        
        imgresult = curl_easy_perform(image);

        if (imgresult) {
            curl_easy_cleanup(image);
            fclose(fp);
            printf("ERROR! on downloading pg.\n");
            return 0;
        }
        curl_easy_cleanup(image);
        fclose(fp);

    // }
    return 1; 
}