package com.example.demo.demo3;

import org.springframework.beans.factory.annotation.Autowire;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class BeanIdTestConfig {

    @Bean
    public BeanTest beanTest() {
        return new BeanIdTestImpl("beanTest");
    }

//    @Bean
//    public BeanTest BEANtest() {
//        return new BeanIdTestImpl("BEANtest");
//    }

//    @Bean
//    public BeanTest Beantest() {
//        return new BeanIdTestImpl("Beantest");
//    }
//
//
//    @Bean(name = {"beanTestX1", "beanTestX3"})
//    public BeanTest beanTest1() {
//        return new BeanIdTestImpl("beanTest1");
//    }
//
//    @Bean(name = {"beanTestX1", "beanTestX2"})
//    public BeanTest beanTest2() {
//        return new BeanIdTestImpl("beanTest2");
//    }
}
