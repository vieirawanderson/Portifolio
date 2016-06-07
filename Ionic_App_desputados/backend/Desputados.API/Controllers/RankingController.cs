using Desputados.API.Models;
using Desputados.API.Repositorio;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;

namespace Desputados.API.Controllers
{
    [RoutePrefix("api/ranking")]
    public class RankingController : ApiController
    {
        [HttpGet]
        [Route("")]
        public IHttpActionResult Get()
        {
            try
            {
                using (var db = new DesputadosContext())
                {
                    var lista = new List<Ranking>();

                    var rankings = db.ranking_usuario
                        .Include("usuarios")
                        .OrderByDescending(x => x.PONTUACAO)
                        .Take(10)
                        .ToList();

                    foreach (var item in rankings)
                        lista.Add(item);

                    return Ok(lista);
                }
            }
            catch (Exception ex)
            {
                return InternalServerError(ex);
            }
        }

        [HttpGet]
        [Route("{idUsuario}")]
        public IHttpActionResult GetRankingUsuario(int idUsuario)
        {
            try
            {
                using (var db = new DesputadosContext())
                {
                    Ranking ranking = null;

                    var rankingUsuario = db.ranking_usuario
                        .Include("usuarios")
                        .Where(x => x.ID_USUARIO == idUsuario)
                        .FirstOrDefault();

                    if (rankingUsuario != null)
                    {
                        ranking = new Ranking()
                        {
                            nomeUsuario = rankingUsuario.usuarios.NOME,
                            pontuacao = rankingUsuario.PONTUACAO
                        };
                    }

                    return Ok(ranking);
                }
            }
            catch (Exception ex)
            {
                return InternalServerError(ex);
            }
        }

        [HttpPost]
        [Route("")]
        public IHttpActionResult Post([FromBody]RankingRequest rankingRequest)
        {
            try
            {
                using (var db = new DesputadosContext())
                {
                    var u = db.usuarios.FirstOrDefault(x => x.ID == rankingRequest.idUsuario);

                    if (u == null)
                    {
                        return Ok(new
                        {
                            sucesso = false,
                            mensagem = "O usuário informado não existe"
                        });
                    }
                    else
                    {
                        var ranking = db.ranking_usuario.FirstOrDefault(x => x.ID_USUARIO == rankingRequest.idUsuario);
                        ranking.PONTUACAO += 1;
                        db.SaveChanges();
                        return Ok(new
                        {
                            sucesso = true,
                            mensagem = ""
                        });
                    }
                }
            }
            catch (Exception ex)
            {
                return InternalServerError(ex);
            }
        }
    }
}
