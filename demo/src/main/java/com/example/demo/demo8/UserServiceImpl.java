package com.example.demo.demo8;

import org.springframework.stereotype.Service;

@Service
public class UserServiceImpl implements UserService {

    @Override
    public void work() {
        System.out.println("work");
    }

}
