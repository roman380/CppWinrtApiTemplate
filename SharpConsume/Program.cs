using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Api;

// NOTE: Add references to 
// - C:\Program Files (x86)\Windows Kits\10\UnionMetadata\10.0.22621.0\Windows.winmd
// - Api.winmd
// and see app.manifest for Api.dll reference

namespace SharpConsume
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
