#pragma once

#include <cstdio>
#include <memory>

std::shared_ptr<FILE> shared_file_ptr(const char *filename, const char *flags);
