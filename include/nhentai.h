#ifndef NHENTAI_H
#define NHENTAI_H

#include <stdlib.h>

#include "download.h"
#include "ntags.h"

typedef struct nhentai {
    char* id;
    char* url;
    char* dir;
    ntags_T* tags;
    curl_T* mem;
} nhentai_T;

nhentai_T* nhentai_init(char* id);
void nhentai_html(nhentai_T* nhentai);
void nhentai_tags(nhentai_T* nhentai);
void nhentai_cbz(nhentai_T* nhentai);
void nhentai_data(nhentai_T* nhentai);
void nhentai_download(nhentai_T* nhentai);

#endif /* NHENTAI_H */