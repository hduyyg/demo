package com.example.demo.demo2;

import org.springframework.stereotype.Component;

@Component
public class COmponentTestImpl2 implements ComponentTest {
    @Override
    public String say() {
        return "COmponentTestImpl2";
    }
}
