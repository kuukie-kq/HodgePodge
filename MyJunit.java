package com.java.main.self;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;

public class MyJunit {
	//����һ������ʵ��
    public static void run(Class c) throws InstantiationException,IllegalAccessException, IllegalArgumentException,InvocationTargetException {
        Method[] methods = c.getDeclaredMethods();//��ȡ���������ķ�������
        List<Method> testList = new ArrayList<Method>();//@Mytestע��ķ�������
        Method afterMethod = null;//@Myafterע�ⷽ��
        Method beforeMethod = null;//@Mybefore��ע�ⷽ��
        for (Method method : methods) {//ѭ���������������з���
        //�����@Mytestע�⣬�򽫸÷������뵽Mytestע��ķ�������
            if (method.isAnnotationPresent(Mytest.class)) {
                testList.add(method);
            }
            //�����@Beforeע�⣬�����ø÷���
            if (method.isAnnotationPresent(Mybefore.class)) {
                beforeMethod = method;
            }
            //�����@Afterע�⣬�����ø÷���
            if (method.isAnnotationPresent(Myafter.class)) {
                afterMethod = method;

            }

        }
        //newһ������ʵ��
        Object obj = c.newInstance();
        //���伤���
        for (Method m : testList) {
            if (beforeMethod != null) {
                beforeMethod.invoke(obj, null);
            }

            m.invoke(obj, null);
            if (afterMethod != null) {
                afterMethod.invoke(obj, null);
            }

        }
    }
}
