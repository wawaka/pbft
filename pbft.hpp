#pragma once

typedef int network_address_t;

static constexpr int F = 2;
static constexpr int N = 3 * F + 1;

extern std::mutex console_mutex;
