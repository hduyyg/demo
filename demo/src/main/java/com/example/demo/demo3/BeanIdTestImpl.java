package com.example.demo.demo3;

import com.example.demo.demo2.ComponentTest;

public class BeanIdTestImpl implements BeanTest {

    private ComponentTest componentTestImpl;

    public ComponentTest getComponentTestImpl() {
        return componentTestImpl;
    }

    public void setComponentTestImpl(ComponentTest componentTestImpl) {
        this.componentTestImpl = componentTestImpl;
    }

    private String word;

    public BeanIdTestImpl(String word) {
        this.word = word;
    }

    @Override
    public String say() {
        return word;
    }
}
