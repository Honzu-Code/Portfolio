"""Add foreign key for blog

Revision ID: b143e364b4e4
Revises: 977f0b4ccf36
Create Date: 2022-07-15 15:04:19.966129

"""
from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision = 'b143e364b4e4'
down_revision = '977f0b4ccf36'
branch_labels = None
depends_on = None


def upgrade() -> None:
    op.add_column("post",sa.Column("blog_fk_key",sa.Integer,sa.ForeignKey("blog.id")))


def downgrade() -> None:
    op.drop_column("post","blog_fk_key")
