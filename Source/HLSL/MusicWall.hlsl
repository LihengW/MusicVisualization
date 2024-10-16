# define PI 3.1415
# define RandSeed 151.3645

struct QuaternionOperation
{
    float4 qmul(float4 q1, float4 q2)
    {
        return float4(
            q2.xyz * q1.w + q1.xyz * q2.w + cross(q1.xyz, q2.xyz),
            q1.w * q2.w - dot(q1.xyz, q2.xyz)
        );
    }

    float3 rotate_vector(float3 v, float4 r)
    {
        float4 r_c = r * float4(-1, -1, -1, 1);
        return qmul(r, qmul(float4(v, 0), r_c)).xyz;
    }

    float4 q_conj(float4 q)
    {
        return float4(-q.x, -q.y, -q.z, q.w);
    }

    float4 q_inverse(float4 q)
    {
        float4 conj = q_conj(q);
        return conj / (q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
    }
};

QuaternionOperation quadop;
meshrotator = SystemRotation;

float4 inversed_quat = quadop.q_inverse(SystemRotation);

float amply = 15.0f;

float3 localpos = quadop.rotate_vector(ParticlePosition - SystemPosition, inversed_quat);

localpos.z = amply * sin((2.0f * ParticlePosition.y + 2.0f * ParticlePosition.x) * PI + 3.0f * Time);

localpos = quadop.rotate_vector(localpos, SystemRotation);

particlepos = SystemPosition + localpos;