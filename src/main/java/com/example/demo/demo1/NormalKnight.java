package com.example.demo.demo1;

import org.springframework.stereotype.Component;

@Sword
@Component
public class NormalKnight implements Knight {

    @Override
    public void fight() {
        System.out.println("这里是普通骑士，只能使出普通一击");
    }
}