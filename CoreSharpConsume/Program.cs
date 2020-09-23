using System;
using Api;

// NOTE: Add references to 
// - C:\Program Files (x86)\Windows Kits\10\UnionMetadata\10.0.18362.0\Windows.winmd
// - Api.winmd
// and see app.manifest for Api.dll reference

namespace CoreSharpConsume
{
    class Program
    {
        static void Main(string[] args)
        {
            var myClass = new MyClass();
            Console.WriteLine($"{myClass.Text}");
        }
    }
}
