"""Add new table post for blog

Revision ID: 977f0b4ccf36
Revises: 
Create Date: 2022-07-15 15:01:42.839729

"""
from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision = '977f0b4ccf36'
down_revision = None
branch_labels = None
depends_on = None



def upgrade():
    op.create_table(
        "post",
        sa.Column("id",sa.Integer(),primary_key=True),
        sa.Column("description",sa.Text()),
        sa.Column("blog_id",sa.Integer()),
    )


def downgrade():
    op.drop_table("post")
