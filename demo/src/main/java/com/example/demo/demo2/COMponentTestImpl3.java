package com.example.demo.demo2;

import org.springframework.stereotype.Component;

@Component(value = "奥利给")
public class COMponentTestImpl3 implements ComponentTest {
    @Override
    public String say() {
        return "奥利给";
    }
}
