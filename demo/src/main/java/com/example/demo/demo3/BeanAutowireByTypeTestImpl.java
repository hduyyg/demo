package com.example.demo.demo3;

public class BeanAutowireByTypeTestImpl implements BeanTest {

    @Override
    public String say() {
        return "验证根据type自动注入";
    }
}
