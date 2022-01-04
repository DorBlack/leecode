#ifndef __TR_MAX_LEN_SUB_STRING_H__
#define __TR_MAX_LEN_SUB_STRING_H__
#include <string>

/**
 * @brief 给你一个字符串 s ，考虑其所有 重复子串 ：即，s 的连续子串，在 s 中出现 2 次或更多次。
 * 这些出现之间可能存在重叠。返回 任意一个 可能具有最长长度的重复子串。如果 s 不含重复子串，那么答案为 "" 。
 * 示例1:
 *      输入：s = "banana"
 *      输出："ana"
 * 示例2:
 *      输入：s = "abcd"
 *      输出：""
 */


//方法一: 二分查找 + rabin-karp

/*大质数作为进制数*/
constexpr size_t rk_prime = 16777619;

size_t rk_pow(size_t base, size_t index)
{
    size_t power = 1;
    while (index) {
        if (index & 0x1) {
            power *= base;
        }
        base *= base;
        index >>= 1;
    }
    return power;
}

size_t rk_hash(char *str, size_t length) 
{
    size_t hash_code = 0;
    if (nullptr != str) {
        while (length) {
            hash_code = (hash_code * rk_prime) + *str;
            str++;
            length--;
        }
    }
    return hash_code;
}

std::string rabin_karp(const std::string& src, const std::string& text)
{
    if (src.size() < text.size()) {
        return std::string();
    }
    size_t text_hash = rk_hash((char*)text.c_str(), text.size());
    size_t power = rk_pow(rk_prime, text.size());
    size_t src_hash = rk_hash((char*)src.substr(0,text.size()).c_str(), text.size());
    if (text_hash == src_hash && text == src.substr(0, text.size())) {
        return text;
    }
    //滑动搜索比较
    size_t len = text.size();
    while (len < src.size()) {
        src_hash = src_hash * rk_prime + src[len] - (power * src[len - text.size()]);
        len++;
        if (src_hash == text_hash && text == src.substr(len - text.size(), text.size())) {
            return text;
        }
    }
    return std::string();
}

//方法二: 后缀数组


#endif