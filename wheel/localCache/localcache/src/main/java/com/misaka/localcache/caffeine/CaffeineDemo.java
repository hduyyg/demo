package com.misaka.localcache.caffeine;

import com.github.benmanes.caffeine.cache.Cache;
import com.github.benmanes.caffeine.cache.Caffeine;

import java.util.concurrent.TimeUnit;

public class CaffeineDemo {

    public static void main(String[] args) {
        CaffeineDemo caffeineDemo = new CaffeineDemo();
        caffeineDemo.test();
    }

    Cache<String, Object> cache = Caffeine.newBuilder()
            .initialCapacity(100)//初始大小
            .maximumSize(200)//最大数量
            .expireAfterWrite(3, TimeUnit.SECONDS)//过期时间
            .build();

    public void test() {
        cache.put("key", "value");
    }
}
