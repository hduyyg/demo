package com.misaka.localcache.cache;

public interface Cache {

    /**
     * 将key放入缓存
     * @param key 缓存的key
     * @param value 缓存的值
     */
    void put(String key, String value);

    /**
     * 从缓存获取值
     * @param key key
     * @return 如果key不存在，会返回null
     */
    String get(String key);
}
