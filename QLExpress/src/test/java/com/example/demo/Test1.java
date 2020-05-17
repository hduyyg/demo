package com.example.demo;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.ComponentScan;

@ComponentScan("com.example.demo")
@SpringBootTest
public class Test1 {

    @Autowired
    private ApplicationContext applicationContext;

    @Test
    public void test() {
        System.out.println("xx");
    }
}
