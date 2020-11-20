#include <ngx_http.h>

static ngx_int_t ngx_http_location_name_vars(ngx_conf_t* cf);

static ngx_http_module_t ngx_http_location_name_module_ctx = {
    ngx_http_location_name_vars, /* preconfiguration */
    NULL, /* postconfiguration */

    NULL, /* create main configuration */
    NULL, /* init main configuration */

    NULL, /* create server configuration */
    NULL, /* merge server configuration */

    NULL, /* create location configuration */
    NULL /* merge location configuration */
};

ngx_module_t ngx_http_location_name_module = {
    NGX_MODULE_V1,
    &ngx_http_location_name_module_ctx,
    NULL,
    NGX_HTTP_MODULE,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NGX_MODULE_V1_PADDING
};

static ngx_int_t
ngx_http_location_name_var_handler(ngx_http_request_t* r,
    ngx_http_variable_value_t* v, uintptr_t data)
{
    ngx_http_core_loc_conf_t* clcf;

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    v->valid = 1;
    v->no_cacheable = 0;
    v->not_found = 0;
    v->len = clcf->name.len;
    v->data = clcf->name.data;

    return NGX_OK;
}

static ngx_int_t
ngx_http_location_name_vars(ngx_conf_t* cf)
{

    ngx_http_variable_t* var;
    static ngx_str_t var_name = ngx_string("current_location_name");

    var = ngx_http_add_variable(cf, &var_name, NGX_HTTP_VAR_NOCACHEABLE);
    if (var == NULL) {
        return NGX_ERROR;
    }

    var->get_handler = ngx_http_location_name_var_handler;
    var->data = 0;

    return NGX_OK;
}
