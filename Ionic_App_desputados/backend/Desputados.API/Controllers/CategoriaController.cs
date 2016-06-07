using Desputados.API.Models;
using Desputados.API.Repositorio;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Threading.Tasks;
using System.Web.Http;
using System.Web.Http.Description;

namespace Desputados.API.Controllers
{
    [RoutePrefix("api/categorias")]
    public class CategoriaController : ApiController
    {
        [HttpGet]
        [Route("")]
        public IHttpActionResult Get()
        {
            try
            {
                using (var db = new DesputadosContext())
                {
                    var lista = new List<Categoria>();

                    foreach (var item in db.categorias)
                        lista.Add(item);


                    return Ok(lista);
                }
            }
            catch (Exception ex)
            {
                return InternalServerError(ex);
            }
        }
    }
}