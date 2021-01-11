package com.misaka.localcache.cache;

import java.util.LinkedHashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

public class CacheImpl implements Cache {

    Map<Object, Object> cache = new ConcurrentHashMap<Object, Object>();

    @Override
    public void put(String key, String value) {
        Map<String, String> map = new LinkedHashMap<>();
        map.put("xx", "yy");
    }

    @Override
    public String get(String key) {
        return null;
    }
}
