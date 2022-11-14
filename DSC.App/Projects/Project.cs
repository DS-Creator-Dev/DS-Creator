using DSC.App.Projects.Components;
using System;
using System.Collections.Generic;
using System.Data.SqlTypes;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Linq;
using System.Xml.Serialization;

namespace DSC.App.Projects
{
    [XmlRoot("Project", IsNullable = false)]
    public class Project
    {
        private string _Name;
        public string Name 
        {
            get => _Name; 
            set
            {
                _Name = value;
                Tree.Root.Name = value;
            }
        }

        /// <summary>
        /// Path containing project's directory
        /// </summary>
        [XmlIgnore]
        public String Path { get; private set; }
                
        /// <summary>
        /// Project Files Tree
        /// </summary>
        public ProjectTree Tree { get; set; } = new ProjectTree();

        public Project() { }

        public Project(string name, string path)
        {
            Name = name;
            Path = path;
            Tree.Root.Name = Name;
            ProjectPath = System.IO.Path.Combine(Path, Name);
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

        /// <summary>
        /// Path containing project's data
        /// </summary>
        [XmlIgnore]
        public string ProjectPath;       

        /// <summary>
        /// Path to project configuration file
        /// </summary>
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
            project.Path = System.IO.Path.GetDirectoryName(path);
            project.ProjectPath = path;
            project.Tree.Root.DeserializeCheck();

            foreach (var node in project.Tree.Root.GetLeaves())
            {
                var item = node.Item;
                item.WorkPath = System.IO.Path.Combine(project.ProjectPath, node.RelativePath);
            }           

            return project;
        }



        public IEnumerable<Asset> GetAssets()
        {
            foreach (var asset in Tree.Root.GetItems(p => p.GetType() == typeof(Asset)))
            {
                yield return (Asset)asset;
            }
            yield break;
        }        

        public void Add(Asset asset, string path)
        {
            var node = TouchPath(path);
            node = node.Add(asset);            
            path = System.IO.Path.Combine(ProjectPath, node.RelativePath);            
            asset.WorkPath = path;
            asset.Save(path);
        }
    }

    class ProjectFileNotFoundException : FileNotFoundException { }
}
