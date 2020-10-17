#ifndef DOWNLOAD_H
#define DOWNLOAD_H

static size_t writeCallBack(char* buf, size_t size, size_t nmemb, void* up);
int getHtml(char* downloadUrl);
int doDownload(char* id, int ind, char* dir, char* ext);

#endif // DOWNLOAD_H