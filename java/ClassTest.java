import java.lang.*;

public class ClassTest
{
	String name;

	public void setName(String n)
	{
		name = n;
	}

	public String getName()
	{
		return name;
	}

	public static void printClassMessage(Object obj)
	{
		//获取类类型
		Class c = obj.getClass();

		//获取类名称
		System.out.println("类的名称是：" + c.getName());

		//获取类中方法对象
		Method[] methods = c.getMethods();
		for (int i = 0; i < methods.length; ++i)
		{
			/*
			 *依次输出类中方法对象
			 */

			 //输出方法返回类型
			 System.out.print((methods[i].getReturnType).getName() + " ");

			 //得到方法的名称
			 System.out.print(methods[i].getName);

			 //获取方法参数列表
			 Class[] paraTypes = methods[i].getParameterTypes();
			 for (Class para : paraTypes)
			 {
			 	System.out.print(para.getName() + " ");	
			 }

			 System.out.println();
		}
		
	}

	public static void main(String[] args)
	{
		printClassMessage(ClassTest);
	}
}
