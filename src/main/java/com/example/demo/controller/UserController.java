package com.example.demo.controller;

import com.example.demo.dao.UserRepository;
import com.example.demo.dao.model.User;
import com.example.demo.model.BaseResponse;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import javax.sql.DataSource;

/**
 * @author yuyan
 */
@RestController
@RequestMapping("/user")
public class UserController {

    @Autowired
    private UserRepository userRepository;
    @Autowired
    private DataSource dataSource;

    @PostMapping("/save")
    public BaseResponse saveUser(User user) {
        userRepository.save(user);
        return BaseResponse.success();
    }

    @GetMapping("/getAll")
    public BaseResponse getAll() {
        return BaseResponse.success(userRepository.findAll());
    }
}
