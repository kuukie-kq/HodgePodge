package com.java.main.proxy;

import java.io.File;
import java.io.FileWriter;
import java.lang.reflect.Constructor;
import java.net.URL;
import java.net.URLClassLoader;

import javax.tools.JavaCompiler;
import javax.tools.StandardJavaFileManager;
import javax.tools.ToolProvider;
import javax.tools.JavaCompiler.CompilationTask;

public class Proxy {
	public static Object newProxyInstance(String str) throws Exception {
        //����JavaԴ�ļ�  
        String srcCode = "package com.java.main.proxy;\n\n"
            + "public class $ProxyTest implements ProxyInter {\n"
            + "\tpublic void run() {\n\t\t"
            + str
            + "\n\t}\n"
            + "}\n";
        String fileName = "d:/MyProgram/workspace/KuukieNOWorld/src/com/java/main/proxy/$ProxyTest.java";  
        File f = new File(fileName);
        FileWriter fw = new FileWriter(f);
        fw.write(srcCode);
        fw.flush();
        fw.close();
        
        //��Java�ļ������class�ļ�
        JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();
        StandardJavaFileManager fileMgr = compiler.getStandardFileManager(null, null, null);
        Iterable units = fileMgr.getJavaFileObjects(fileName);
        CompilationTask t = compiler.getTask(null, fileMgr, null, null, null, units);
        t.call();
        fileMgr.close();
        
        //���ص��ڴ棬��ʵ����
        URL[] urls = new URL[] {new URL("file:/" + "D:/MyProgram/workspace/KuukieNOWorld/src/")};
        URLClassLoader ul = new URLClassLoader(urls);
        Class c = ul.loadClass("com.java.main.proxy.$ProxyTest");
        
        Constructor ctr = c.getConstructor();
        Object m = ctr.newInstance();
        
        return m;
	}
}
