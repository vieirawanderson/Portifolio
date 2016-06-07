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
    [RoutePrefix("api/questoes")]
    public class QuestaoController : ApiController
    {
        [HttpGet]
        [Route("{idCategoria}")]
        public IHttpActionResult Get(int? idCategoria)
        {
            try
            {
                using (var db = new DesputadosContext())
                {
                    var lista = new List<Questao>();

                    var questoes = db.questoes
                        .Include("alternativas")
                        .Where(x => x.ID_CATEGORIA == idCategoria);

                    foreach (var questao in questoes)
                        lista.Add(questao);

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