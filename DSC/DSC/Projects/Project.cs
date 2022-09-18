using DSC.Projects.Components;
using System;
using System.Collections.Generic;
using System.Data.SqlTypes;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Serialization;

namespace DSC.Projects
{
    [XmlRootAttribute("Project", IsNullable = false)]
    public class Project
    {
        public string Name { get; set; }

        [XmlIgnore]
        public String Path { get; private set; }
                
        public ProjectTree Tree { get; set; } = new ProjectTree();

        public Project() { }

        public Project(string name, string path)
        {
            Name = name;
            Path = path;
            Tree.Root.Name = Name;            
            Directory.CreateDirectory(ProjectPath);
            TouchPath("Actors");
            TouchPath("Assets");
            TouchPath("Scenes");
            TouchPath("Sound");
        }

        public ProjectTreeNode TouchPath(string relPath)
        {
            Directory.CreateDirectory(System.IO.Path.Combine(ProjectPath, relPath));
            return Tree.Add(relPath);
        }

        [XmlIgnore]
        public string ProjectPath
        {
            get => System.IO.Path.Combine(Path, Name);
        }

        [XmlIgnore]
        public string InfoPath
        {
            get => System.IO.Path.Combine(ProjectPath, ".DSC");
        }

        public void Save()
        {
            XmlSerializer serializer = new XmlSerializer(typeof(Project));
            TextWriter writer = new StreamWriter(InfoPath);
            serializer.Serialize(writer, this);
            writer.Close();
        }

        public static Project Load(string path)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(Project));
            Project project;
            var prjfile = System.IO.Path.Combine(path, ".DSC");
            if (!File.Exists(prjfile))
            {
                throw new ProjectFileNotFoundException();
            }
            using (TextReader reader = new StreamReader(prjfile))
            {
                 project = serializer.Deserialize(reader) as Project;
            }            
            project.Path = System.IO.Path.Combine(path, "..");
            project.Tree.Root.DeserializeCheck();            
            return project;

        }

        void LoadItem()
        {

        }

        public void Add(Asset asset, string path)
        {
            var node = TouchPath(path);
            node = node.Add(asset);            
            path = System.IO.Path.Combine(ProjectPath, node.RelativePath);
            MessageBox.Show(path);
            asset.Save(path);
        }
    }

    class ProjectFileNotFoundException : FileNotFoundException { }
}
