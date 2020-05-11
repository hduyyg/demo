package com.example.demo.demo7;

import com.lmax.disruptor.EventFactory;

public class LongEventFactory implements EventFactory {
    @Override
    public Object newInstance() {
        return new LongEvent();
    }
}