package com.example.demo.model;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class BaseResponse implements Serializable {

    /**
     * 错误码
     * 0 代表正常，1 代表异常
     */
    private Integer code;
    private String msg;
    private Object data;

    public static BaseResponse success() {
        BaseResponse response = new BaseResponse();
        response.setCode(0);
        response.setMsg("ok");
        return response;
    }

    public static BaseResponse success(Object data) {
        BaseResponse response = new BaseResponse();
        response.setCode(0);
        response.setMsg("ok");
        response.setData(data);
        return response;
    }

    public static BaseResponse fail(String msg) {
        BaseResponse response = new BaseResponse();
        response.setCode(1);
        response.setMsg(msg);
        return response;
    }
}