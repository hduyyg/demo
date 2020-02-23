package com.example.demo.controller;

import com.example.demo.model.BaseResponse;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.ResponseBody;

/**
 * 全局异常处理
 * @author yuyan
 */
@ControllerAdvice
public class ApiControllerAdvice {

    @ResponseBody
    @ExceptionHandler(value = Exception.class)
    public BaseResponse errorHandler(Exception ex) {
        return BaseResponse.fail(ex.getMessage());
    }
}
