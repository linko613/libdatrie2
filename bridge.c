#include "datrie/trie.h"
#include <windows.h>

// 易语言标准调用约定
#define EAPI __declspec(dllexport) __stdcall

EAPI Trie* Trie_Create() {
    AlphaMap *amap = alpha_map_new();
    if (!amap) return NULL;
    alpha_map_add_range(amap, 0x00, 0xff);
    Trie *trie = trie_new(amap);
    alpha_map_free(amap);
    return trie;
}

EAPI BOOL Trie_Add(Trie *trie, const char *key, int data) {
    if (!trie || !key) return FALSE;
    return trie_store(trie, (const AlphaChar *)key, (TrieData)data);
}

EAPI BOOL Trie_Del(Trie *trie, const char *key) {
    if (!trie || !key) return FALSE;
    return trie_delete(trie, (const AlphaChar *)key);
}

EAPI int Trie_Search(Trie *trie, const char *key) {
    TrieData data;
    if (trie && trie_retrieve(trie, (const AlphaChar *)key, &data)) {
        return (int)data;
    }
    return -1;
}

EAPI void Trie_Free(Trie *trie) {
    if (trie) trie_free(trie);
}
