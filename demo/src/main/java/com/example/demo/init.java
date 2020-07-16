package com.example.demo;

import com.example.demo.demo8.UserService;
import org.springframework.beans.factory.InitializingBean;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

@Component
public class init implements InitializingBean {

    @Autowired
    private UserService userService;

    @Override
    public void afterPropertiesSet() throws Exception {
        userService.work();
    }
}
