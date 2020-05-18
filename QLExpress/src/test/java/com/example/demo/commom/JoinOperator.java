package com.example.demo.commom;

import com.ql.util.express.Operator;

/**
 * @author houbinbin
 */
public class JoinOperator extends Operator {

    @Override
    public Object executeInner(Object[] objects) {
        java.util.List result = new java.util.ArrayList();

        for (Object object : objects) {
            if (object instanceof java.util.List) {
                result.addAll(((java.util.List) object));
            } else {
                result.add(object);
            }
        }

        return result;
    }
}