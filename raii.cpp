#pragma once
#include "pch.h"
#include "raii.h"


// https://codereview.stackexchange.com/questions/4679/shared-ptr-and-file-for-wrapping-cstdio-update-also-dlfcn-h

std::shared_ptr<FILE> shared_file_ptr(const char *filename, const char *flags)
{
    FILE *f;
    fopen_s(&f, filename, flags);
    auto sp = std::shared_ptr<FILE>(f, [](auto p) { 
        if (p) 
            fclose(p); 
    });

    return sp;
}
