package com.example.demo.demo1;

public class Armyfactory {

    private Knight knight;

    public Armyfactory(Knight knight) {
        this.knight = knight;
    }

    public void fight() {
        knight.fight();
    }
}
