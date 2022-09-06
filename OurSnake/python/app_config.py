
def default_app_port():
    return 5000

def set_app_config(app):
    app.config['MYSQL_DATABASE_USER'] = 'test'
    app.config['MYSQL_DATABASE_PASSWORD'] = 'LovePy$1'
    app.config['MYSQL_DATABASE_DB'] = 'snakes'
    app.config['MYSQL_DATABASE_HOST'] = 'localhost'
    pass
