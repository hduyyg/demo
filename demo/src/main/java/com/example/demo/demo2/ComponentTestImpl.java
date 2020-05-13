package com.example.demo.demo2;

import com.example.demo.demo3.BeanTest;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

@Component
public class ComponentTestImpl implements ComponentTest {

    @Override
    public String say() {
        return "ComponentTestImpl";
    }
}
