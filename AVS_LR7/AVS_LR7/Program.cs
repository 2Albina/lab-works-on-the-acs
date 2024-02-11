
using System.Text;

namespace AVS_LR7
{
    class Program
    {
        static void Main(string[] args)
        {
            Encoding.RegisterProvider(CodePagesEncodingProvider.Instance);
            Encoding ansi = Encoding.GetEncoding("ASCII");
            Encoding utf8 = Encoding.GetEncoding("UTF-8");
            var utf8WithoutBOM = new System.Text.UTF8Encoding(false);
            try
            {
                var sr = new StreamReader("input1.txt");
                var text = sr.ReadToEnd();

                if (text != "")
                {
                    string outstr = "";
                    var c = Encoding.Default.GetChars(Encoding.Default.GetBytes(text));


                    byte[] ansiBytes = ansi.GetBytes(c);
                    //ansiBytes.Reverse();
                    byte[] utf8Bytes = Encoding.Convert(ansi, utf8, ansiBytes);
                    outstr += utf8.GetString(utf8Bytes);
                    Console.WriteLine($"Исходные данные в кодировке ANSI:\n {text}");
                    Console.WriteLine("\n");
                    Console.WriteLine($"Полученные данные в кодировке UTF8:\n {outstr}");
                    using (StreamWriter sw = new StreamWriter("output_utf8.txt", false, Encoding.GetEncoding("utf-8")))

                    //using (StreamWriter sw = new StreamWriter("output_utf8.txt",false,  new System.Text.UTF8Encoding(false)))
                    {
                        sw.WriteLine(outstr);
                    }


                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                Console.WriteLine("Ошибка, нет входного файла");
            }

        }
    }
}