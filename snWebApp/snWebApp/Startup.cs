using Microsoft.Owin;
using Owin;

[assembly: OwinStartupAttribute(typeof(snWebApp.Startup))]
namespace snWebApp
{
    public partial class Startup
    {
        public void Configuration(IAppBuilder app)
        {
            ConfigureAuth(app);
        }
    }
}
