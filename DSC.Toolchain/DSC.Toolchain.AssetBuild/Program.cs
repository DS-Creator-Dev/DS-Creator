using SixLabors.ImageSharp;
using SixLabors.ImageSharp.Metadata.Profiles.Exif;
using SixLabors.ImageSharp.PixelFormats;
using System.Collections;
using System.IO;

class ConvertedData
{
    public short[] Gfx = new short[0];
    public short[] Palette = new short[0];

    public byte[] ToBytes()
    {
        short[] result = Gfx.Concat(Palette).ToArray();
        byte[] rb = new byte[result.Length * 2];
        Buffer.BlockCopy(result, 0, rb, 0, rb.Length);
        return rb;
    }

    public short[] ToShorts()
    {
        short[] result = Gfx.Concat(Palette).ToArray();
        return result;
    }
}

class AssetWriter
{
    public string Name = "";

    public int Width;
    public int Height;
    public int ColorDepth;
    public bool IsBitmap;
    public short[] Data = new short[0];
    public bool IsFile;

    public string? Filename = null;

    public void WriteHeader(string path)
    {
        using(StreamWriter writer = new(path))
        {
            writer.WriteLine("#pragma once");
            writer.WriteLine("#include <DSC>");
            writer.WriteLine("");
            writer.WriteLine($"extern const DSC::AssetData {Name};");
        }
    }

   int ColorDepthFlag
    {
        get => ColorDepth == 4 ? 1 : (ColorDepth == 8 ? 2 : (ColorDepth == 16 ? 3 : 0));
    }

    public short Flags
    {
        get => (short)(
            (IsFile ? 1 : 0)          // ROD_IS_FILE
            | (1<<2)                  // ROD_TYPE_ASSET
            | (IsBitmap ? 1:0) << 8   // ROA_IS_BITMAP
            | (ColorDepthFlag) << 9   // ROA_COLOR_DEPTH
            );
    }

    public void WriteAssembly(string path)
    {
        using (StreamWriter writer = new(path))
        {
            writer.WriteLine($"  .section .rodata");
            writer.WriteLine($"  .align 2");
            writer.WriteLine($"  .global {Name}");
            writer.WriteLine($"  .hidden {Name}");
            writer.WriteLine($"{Name}:");

            // write header
            // Header size (2 bytes) = 16
            // Data Length (4 bytes)
            // Data source (4 bytes)
            // Flags       (2 bytes)
            // Width       (2 bytes)
            // Height      (2 bytes)
            short[] header = new short[8];
            header[0] = 16;
            header[1] = (short)((2*Data.Length) % 65536);
            header[2] = (short)((2*Data.Length) / 65536);
            header[3] = 0; // .....
            header[4] = 0; // .....
            header[5] = Flags;
            header[6] = (short)Width;
            header[7] = (short)Height;

            writer.WriteLine("\n  @ Resource Header");
            string hline = " .hword ";
            for (int i=0;i<8;i++)
            {
                string hword = header[i].ToString("X4");
                hline += (i > 0 ? ", " : "") + "0x" + hword;
            }
            writer.WriteLine(hline);

            if (!IsFile)
            {
                writer.WriteLine("\n  @ Resource Data");
                // write effective data
                for (int i = 0; i < Data.Length; i += 16)
                {
                    string line = " .hword ";
                    int lim = Math.Min(16, Data.Length - i);
                    for (int j = 0; j < lim; j++)
                    {
                        string hword = Data[i + j].ToString("X4");
                        line += (j > 0 ? ", " : "") + "0x" + hword;
                    }
                    writer.WriteLine(line);
                }
            }
            else
            {
                Console.WriteLine("Effective data exists in file. To be implemented...");
                Environment.Exit(-1);
            }
        }
    }
}

static class _
{
    public static short ToBGR15(this Rgba32 color)
    {
        short r = color.R; r /= 8;
        short g = color.G; g /= 8;
        short b = color.B; b /= 8;
        short cl = (short)(r + 32 * g + 32 * 32 * b);
        return cl;
    }
    public static ConvertedData Convert(this Image<Rgba32> image, int color_depth, bool tiles)
    {
        if (color_depth < 16)
        {
            Dictionary<Rgba32, short> colors = new Dictionary<Rgba32, short>();

            image.ProcessPixelRows(accessor =>
            {
                for (int y = 0; y < accessor.Height; y++)
                {
                    Span<Rgba32> pixelRow = accessor.GetRowSpan(y);
                    for (int x = 0; x < accessor.Width; x++)
                    {
                        if (!colors.ContainsKey(pixelRow[x]))
                        {
                            colors[pixelRow[x]] = (short)colors.Count;
                            if (colors.Count > (1 << color_depth)) 
                            {
                                throw new InvalidDataException("Invalid color depth.");
                            }
                        }
                    }
                }                
            });
            Console.WriteLine($"Palette size = {colors.Count} / {(1 << color_depth)}");
            ConvertedData data = new ConvertedData();
            data.Gfx = new short[image.Width * image.Height * color_depth / 8 / sizeof(short)];

            Console.WriteLine($"Generating graphics...");
            image.ProcessPixelRows(accessor =>
            {
                int k = 0;
                if (!tiles)
                {
                    for (int y = 0; y < accessor.Height; y++)
                    {
                        Span<Rgba32> pixelRow = accessor.GetRowSpan(y);
                        for (int x = 0; x < accessor.Width; x++)
                        {
                            short index = colors[pixelRow[x]];
                            if (color_depth == 8)
                            {
                                data.Gfx[k / 2] |= (short)(index << (8 * (k % 2)));
                                k++;
                            }
                            else if (color_depth == 4)
                            {
                                data.Gfx[k / 4] |= (short)(index << (4 * (k % 4)));
                                k++;
                            }
                        }
                    }
                }
                else
                {
                    for (int ty = 0; ty < accessor.Height / 8; ty++)
                    {
                        for(int tx = 0;tx<accessor.Width/8;tx++)
                        {
                            for(int iy=0;iy<8;iy++)
                            {
                                int y = 8 * ty + iy;
                                Span<Rgba32> pixelRow = accessor.GetRowSpan(y);
                                for (int ix = 0; ix < 8; ix++)
                                {
                                    int x = 8 * tx + ix;
                                    short index = colors[pixelRow[x]];
                                    if (color_depth == 8)
                                    {
                                        data.Gfx[k / 2] |= (short)(index << (8 * (k % 2)));
                                        k++;
                                    }
                                    else if (color_depth == 4)
                                    {
                                        data.Gfx[k / 4] |= (short)(index << (4 * (k % 4)));
                                        k++;
                                    }
                                }
                            }
                        }
                    }
                }
            });
            Console.WriteLine($"Generating palette...");
            data.Palette = new short[colors.Count];
            int k = 0;
            foreach(var color in colors.Keys)
            {                
                data.Palette[k++] = color.ToBGR15();
            }
            return data;
        }
        else
        {
            ConvertedData data = new ConvertedData();
            data.Gfx = new short[image.Width * image.Height * 2];

            Console.WriteLine($"Generating graphics...");
            image.ProcessPixelRows(accessor =>
            {
                int k = 0;
                for (int y = 0; y < accessor.Height; y++)
                {
                    Span<Rgba32> pixelRow = accessor.GetRowSpan(y);
                    for (int x = 0; x < accessor.Width; x++)
                    {
                        data.Gfx[k++] = pixelRow[x].ToBGR15();
                    }
                }
            });

            return data;
        }        
    }
}

internal partial class Program
{    
    private static void Main(string[] args)
    {
        Console.WriteLine("DSC Asset build tool\n");

        if(args.Length==0)
        {
            Console.WriteLine("AssetBuild <filename \"*.(4|8|16)bpp.png\"> <-wram|-file> <-bitmap|-tiles>");
            Console.WriteLine("           <out_header.h> <out_asm.s> [<resource_filename.roa>]");
        }

        string? filename = args.Length > 0 ? args[0] : null;
        string? output = args.Length > 1 ? args[1] : "-wram";
        string? type = args.Length > 2 ? args[2] : "-tiles";
        string? h_path = args.Length > 3 ? args[3] : null;
        string? s_path = args.Length > 4 ? args[4] : null;
        string? roa_path = args.Length > 5 ? args[5] : null;

        validateFilename(filename);
        validateOutput(output);
        validateType(type);
        validateHPath(h_path);
        validateSPath(s_path);

        int colorDepth = int.Parse(string.Join('\0', filename.Split('.')
            .SkipLast(1).TakeLast(1).ToList()[0]
            .SkipLast(3)));
        Console.WriteLine($"Output color depth = {colorDepth} bits per pixel");

        try
        {
            using (Image<Rgba32> image = Image.Load<Rgba32>(filename))
            {
                validateImage(image);
                ConvertedData converted = image.Convert(colorDepth, type == "-tiles");

                var writer = new AssetWriter();
                writer.Name = "ROA_" + Path.GetFileName(filename).Split('.')[0] + colorDepth.ToString();
                writer.Width = image.Width / 8;
                writer.Height = image.Height / 8;
                writer.IsBitmap = type == "-bitmap";
                writer.ColorDepth = colorDepth;
                writer.Data = converted.ToShorts();
                writer.IsFile = output == "-file";

                writer.WriteHeader(h_path);
                writer.WriteAssembly(s_path);
            }
        }
        catch (Exception e)
        {
            Console.WriteLine("Could not process the image");
            Console.WriteLine(e.Message);
        }              
    }

    static void validateImage(Image img)
    {
        if (img.Width % 8 != 0 || img.Height % 8 != 0)
        {
            throw new ArgumentException("Image sizes must be multiple of 8.");  
        }
    }

    static void validateFilename(string? filename)
    {
        if (filename == null)
        {
            Console.WriteLine("No filename specified.");
            Environment.Exit(-1);
        }
        if (!(filename.EndsWith(".4bpp.png")
          || filename.EndsWith(".8bpp.png")
          || filename.EndsWith(".16bpp.png")
            ))
        {
            Console.WriteLine("Invalid filename. File must end with one of the following extensions:");
            Console.WriteLine("'.4bpp.png', '.8bpp.png', '.16bpp.png'");
            Environment.Exit(-1);
        }

        if (!File.Exists(filename))
        {
            Console.WriteLine("Specified path does not exist.");
            Environment.Exit(-1);
        }

        Console.WriteLine($"Processing file: '{filename}'");
    }

    static void validateOutput(string? output)
    {        
        if (output != "-file" && output != "-wram")
        {
            Console.WriteLine("Invalid output.");
            Environment.Exit(-1);
        }
    }
    static void validateType(string? type)
    {
        if (type != "-tiles" && type != "-bitmap") 
        {
            Console.WriteLine("Invalid type.");
            Environment.Exit(-1);
        }
    }

    static void validateHPath(string? h_path)
    {
        if(h_path == null)
        {
            Console.WriteLine("Missing output header path.");
            Environment.Exit(-1);
        }
    }
    static void validateSPath(string? s_path)
    {
        if (s_path == null)
        {
            Console.WriteLine("Missing output asm path.");
            Environment.Exit(-1);
        }
    }
}
