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
    [RoutePrefix("api/usuario")]
    public class UsuarioController : ApiController
    {
        [HttpGet]
        [Route("")]
        public IHttpActionResult Get(string email)
        {
            try
            {
                var mensagem = "";
                var sucesso = true;
                using (var db = new DesputadosContext())
                {
                    var usuario = db.usuarios.FirstOrDefault(x => x.EMAIL == email);

                    if (usuario == null)
                    {
                        return Ok(new
                        {
                            sucesso = false,
                            mensagem = "O usuário informado não existe"
                        });
                    }

                    return Ok(new
                    {
                        usuario = new Usuario()
                        {
                            id = usuario.ID,
                            email = usuario.EMAIL,
                            nome = usuario.NOME
                        },
                        sucesso = sucesso,
                        mensagem = mensagem
                    });
                }
            }
            catch (Exception ex)
            {
                return InternalServerError(ex);
            }
        }

        [HttpPost]
        [Route("")]
        public IHttpActionResult Post([FromBody]Usuario usuario)
        {
            try
            {
                int? idUsuario = null;
                using (var db = new DesputadosContext())
                {
                    var u = db.usuarios.FirstOrDefault(x => x.EMAIL == usuario.email);

                    if (u != null)
                    {
                        return Ok(new
                        {
                            idUsuario = idUsuario,
                            sucesso = false,
                            mensagem = "O usuário informado já está cadastrado"
                        });
                    }
                    else
                    {
                        using (var tran = db.Database.BeginTransaction())
                        {
                            try
                            {
                                var novoUsuario = db.usuarios.Add(new usuarios()
                                {
                                    NOME = usuario.nome,
                                    EMAIL = usuario.email
                                });

                                db.SaveChanges();

                                db.ranking_usuario.Add(new ranking_usuario()
                                {
                                    ID_USUARIO = novoUsuario.ID,
                                    PONTUACAO = 0
                                });

                                db.SaveChanges();

                                tran.Commit();

                                return Ok(new
                                {
                                    idUsuario = novoUsuario.ID,
                                    sucesso = true,
                                    mensagem = ""
                                });
                            }
                            catch (Exception ex)
                            {
                                tran.Rollback();

                                throw ex;
                            }
                        }
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
