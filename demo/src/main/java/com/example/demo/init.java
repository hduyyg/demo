package com.example.demo;

import org.springframework.beans.factory.InitializingBean;
import org.springframework.stereotype.Component;

@Component
public class init implements InitializingBean {

    @Override
    public void afterPropertiesSet() throws Exception {
    }
}
